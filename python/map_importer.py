#python
import modo,os
from struct import unpack,calcsize,Struct

class OpenShape:
	
	def __init__(self, f):
		
		self.SHP_NAME = os.path.splitext(os.path.basename(f))[0]
		self.shp_path = f
		self.shx_path = os.path.splitext(f)[0] + '.shx'
		self.dbf_path = os.path.splitext(f)[0] + '.dbf'
		
		self.shx = open(self.shx_path, 'rb')
		self.shp = open(self.shp_path, 'rb')
		self.dbf = open(self.dbf_path, 'rb')
		
		self.dbf_data = self.__Read_dbf()
		
	def readshape(self):
		
		shx = self.shx
		shx.seek(32)
		
		shape_type = unpack('<i',shx.read(4))[0]
		
		if shape_type == 3:
			
			self.__ReadPolyLine()
			
		elif shape_type == 5:
			
			self.__ReadPolygon()

	#--DBF読み込み---------------------------------------------------			
	def __Read_dbf(self):
		
		dbf = self.dbf
		
		numRecords, dbfHdrLength, recordLength = unpack('<4xLHH20x',dbf.read(32))

		numFields = (dbfHdrLength-33)//32

		fields=[]

		for i in range(numFields):
	
			fieldDesc = list(unpack('<11sc4xBB14x',dbf.read(32)))

			if b'\x00' in fieldDesc[0]:
	
				idx = fieldDesc[0].index(b'\00')
	
			else:
		
				idx = len(fieldDesc[0]) - 1
	
			fieldDesc[0] = fieldDesc[0][:idx]
	
			fields.append(fieldDesc)

		dbf.seek(dbfHdrLength + 1)

		fmt = ''.join(['%ds' % fieldinfo[2] for fieldinfo in fields])
		fmtSize = calcsize(fmt)

		while fmtSize < recordLength:
			
			fmt += 'x'
			fmtSize += 1
		
		recStruct = Struct(fmt)
		
		record = []
		
		for i in range(numRecords):
		
			recordContents = recStruct.unpack(dbf.read(recStruct.size))
			
			d = []
			
			for value in recordContents:
			
				 d.append(value)
			
			record.append(d)

		return fields,record
	
	#--ポリライン読み込み----------------------------------------------------
	def __ReadPolyLine(self):
		
		shx = self.shx
		shp = self.shp
		
		shx.seek(24)	
		shxLength = (unpack('>i', shx.read(4))[0] * 2) - 100
		shxNumRecords = shxLength // 8
		shx.seek(100)
		
		mesh = modo.Scene().addMesh()
		mesh.name = self.SHP_NAME
		
		geo = mesh.geometry
		vert = geo.vertices
		poly = geo.polygons
		
		dbfrow = 0
		
		while shx.tell() < shxLength + 100:
			
			idx = unpack('>i', shx.read(4))[0] * 2
			reclen = unpack('>i', shx.read(4))[0]
			
			shp.seek(idx + 8 + 36)
			numParts = unpack('<i', shp.read(4))[0]
			numPoints = unpack('<i', shp.read(4))[0]
			Parts = list(unpack('<%si' %numParts, shp.read(4 * numParts)))
						
			posList = []			
			
			#dbf 表示区分------------------------------------------------------------
			
			try:
	
				if self.dbf_data[0][7][0] == b'\x95\\\x8e\xa6\x8b\xe6\x95\xaa':

					visible_type =  self.dbf_data[1][dbfrow][7]
					
				else:
					
					visible_type = ''
					
			except:
				
					visible_type = ''	
			
			#dbf 種別------------------------------------------------------------
			
			try:
	
				if self.dbf_data[0][8][0] == b'\x8e\xed\x95\xca':

					line_type =  self.dbf_data[1][dbfrow][8]
					
				else:
					
					line_type = ''
					
			except:
				
					line_type = ''	
			
			#dbf 標高------------------------------------------------------------
			
			try:
	
				if self.dbf_data[0][9][0] == b'\x95W\x8d\x82':

					height =  float(self.dbf_data[1][dbfrow][9])
					
				else:
					
					height = 0.0
					
			except:
				
					height = 0.0
						
			dbfrow += 1
			
			for i in range(numPoints):
				
				pos = unpack('<2d', shp.read(16))
				pos = modo.Vector3(pos[0],height,-pos[1])
					
				posList.append(pos)
				
			v = []
						
			if len(Parts) == 1:
				
				flg = ''
				
				if posList[0] == posList[-1]:
					
					del posList[-1]
					
					flg = 'close'
				
				for i in posList:
					
					v.append(vert.new(i))
				
				if flg == 'close':v.append(v[0])
				
				if len(v) == 2: v.append(v[-1])
					
				newpoly = poly.new(v,0,lx.symbol.iPTYP_LINE)
				
				if visible_type != '' : newpoly.setTag(lx.symbol.i_POLYTAG_PART,visible_type)
				if line_type != '' : newpoly.setTag(lx.symbol.i_POLYTAG_PICK,line_type)
				if height != 0.0: newpoly.setTag(lx.symbol.i_POLYTAG_PICK,str(height))
								
			else:
				
				del Parts[0]
				
				Parts.append(numPoints)
				
				n = 0
				temp = []			
			
				for i in posList:
								
					temp.append(i)
				   
					n += 1
				
					if n == Parts[0]:
						
						if temp[0] == temp[-1]: 
							
							del temp[-1]
							
							flg = 'close'
						
						for j in temp:
							
							v.append(vert.new(j))
						
						if flg == 'close':v.append(v[0])
						
						if len(v) == 2: v.append(v[-1])
						
						newpoly = poly.new(v,0,lx.symbol.iPTYP_LINE)
						
						if visible_type != '' :newpoly.setTag(lx.symbol.i_POLYTAG_PART,visible_type)
						if line_type != '' :newpoly.setTag(lx.symbol.i_POLYTAG_PICK,line_type)

						temp = []
						v = []
						
						del Parts[0]
				
		geo.setMeshEdits()
		
		mesh.select(1)
		

	#--ポリゴン読み込み---------------------------------------------------
	def __ReadPolygon(self):
		
		shx = self.shx
		shp = self.shp
		
		shx.seek(24)	
		shxLength = (unpack('>i', shx.read(4))[0] * 2) - 100
		shxNumRecords = shxLength // 8
		shx.seek(100)
		
		mesh = modo.Scene().addMesh()
		mesh.name = self.SHP_NAME
		
		geo = mesh.geometry
		vert = geo.vertices
		poly = geo.polygons
		
		dbfrow = 0
		
		while shx.tell() < shxLength + 100:
			
			idx = unpack('>i', shx.read(4))[0] * 2
			reclen = unpack('>i', shx.read(4))[0]
			
			shp.seek(idx + 8 + 36)
			numParts = unpack('<i', shp.read(4))[0]
			numPoints = unpack('<i', shp.read(4))[0]
			Parts = list(unpack('<%si' %numParts, shp.read(4 * numParts)))
						
			posList = []			
			
			for i in range(numPoints):
				
				pos = unpack('<2d', shp.read(16))
				pos = modo.Vector3(pos[0],0.0,-pos[1])
					
				posList.append(pos)
				
			v = []
			
			#dbf 建物種別------------------------------------------------------------
			
			try:
	
				if self.dbf_data[0][8][0] == b'\x8e\xed\x95\xca':

					archi_type =  self.dbf_data[1][dbfrow][8]
					
				else:
					
					archi_type = ''
					
			except:
				
					archi_type = ''	
						
			dbfrow += 1
			
			#-----------------------------------------------------------------------
			
			if len(Parts) == 1:
				
				if posList[0] == posList[-1]: del posList[-1]
			
				for i in posList:
					
					v.append(vert.new(i))
				
				newpoly = poly.new(v,1)
				
				if archi_type != '' : newpoly.setTag(lx.symbol.i_POLYTAG_PICK,archi_type)
				
			else:
				
				del Parts[0]
				
				Parts.append(numPoints)
				
				n = 0
				temp = []			
			
				for i in posList:
								
					temp.append(i)
				   
					n += 1
				
					if n == Parts[0]:
						
						if temp[0] == temp[-1]: del temp[-1]
						
						for j in temp:
							
							v.append(vert.new(j))
						
						newpoly = poly.new(v,1)
						
						newpoly.setTag(lx.symbol.i_POLYTAG_PART,'Possibility of holes')
						
						if archi_type != '' : newpoly.setTag(lx.symbol.i_POLYTAG_PICK,archi_type)
						
						temp = []
						v = []
						
						del Parts[0]
				
		geo.setMeshEdits()
		
		mesh.select(1)
		
		lx.eval('poly.flip')
		lx.eval('poly.flip')
		lx.eval('select.polygon add type nonplanar 11')
		lx.eval('poly.triple')
		lx.eval('poly.merge')
		lx.eval('select.drop polygon')
	
	def close(self):
	
		self.shp.close()
		self.shx.close()
		self.dbf.close()

#--main-------------------------------------------------------------------------------------------------

filename = modo.dialogs.customFile('fileOpen','Open File',('shp',),('Esli Shape File',),('*.shp',))

shape = OpenShape(filename)
shape.readshape()
shape.close()