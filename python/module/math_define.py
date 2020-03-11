#共通処理をまとめておく
from enum import Enum
from enum import auto
import re
import random
import os
import numpy as np
import cv2
import pandas as pd
import shutil
import matplotlib as plt

#定義群========================================================
#==============================================================
HashStr = "#"

#文字列
ZEN = "".join(chr(0xff01 + i) for i in range(94))
HAN = "".join(chr(0x21 + i) for i in range(94))
ZEN2HAN = str.maketrans(ZEN, HAN)
HAN2ZEN = str.maketrans(HAN, ZEN)



#関数群========================================================
#==============================================================
#インクリメント
def INC_VAL(in_val):
    in_val = in_val + 1
    return in_val

#――――――――――――――――――――――――――――――――――――――――――――――――――――――――
#デクリメント
def DEC_VAL(in_val):
    in_val = in_val - 1
    return in_val

#――――――――――――――――――――――――――――――――――――――――――――――――――――――――
#クリア
def CLR_VAL(in_val):
    in_val = 0
    return in_val

#――――――――――――――――――――――――――――――――――――――――――――――――――――――――
#全角→半角
def STRCONVZ2H(in_Str):
    returnStr = in_Str.translate(ZEN2HAN)
    return returnStr

#――――――――――――――――――――――――――――――――――――――――――――――――――――――――
#半角⇒全角
def STRCONVH2Z(in_Str):
    returnStr = in_Str.translate(HAN2ZEN)
    return returnStr

#――――――――――――――――――――――――――――――――――――――――――――――――――――――――
#文字列の数値判定
def ISNUM(s):
    try:
        float(s)        #数値に変換できる文字列にTrueを返す
    except ValueError:
        return False
    else:
        return True

#――――――――――――――――――――――――――――――――――――――――――――――――――――――――
#入力したリストを特定のキーで分割する(ハッシュタグ分割)
def divStrByKey(in_Str, in_key):
    divStr = str(in_key)
    returnList = []
    divmoji = "["
    hanStr = STRCONVZ2H(divStr)       #キーの半角・全角をまとめて格納
    zenStr = STRCONVH2Z(divStr)
    divmoji = divmoji + zenStr + hanStr
    divmoji = divmoji + ']'
    tmpList = re.split(divmoji, in_Str)    #re.split([任意文字],Str)…複数の区切り文字でStrを分割

    for element in tmpList:
        #空白文字の削除
        element = element.strip()       #文字前後の空白文字(全半角スペース)を削除
        #追加
        if 0 != len(element):
            returnList.append(divStr + element)

    return returnList

#――――――――――――――――――――――――――――――――――――――――――――――――――――――――
#乱数生成(重複あり)
#in_min <= x <= in_maxなので注意
def rand_ints_dup(in_min, in_max, in_size):
  return [random.randint(in_min, in_max) for i in range(in_size)]
#――――――――――――――――――――――――――――――――――――――――――――――――――――――――
# 乱数生成(重複無し)
#in_min <= x <= in_maxなので注意
def rand_ints_nodup(in_min, in_max, in_size):
  ns = []
  while len(ns) < in_size:
    n = random.randint(in_min, in_max)
    if not n in ns:
      ns.append(n)
  return ns
#――――――――――――――――――――――――――――――――――――――――――――――――――――――――

#――――――――――――――――――――――――――――――――――――――――――――――――――――――――
#入力ディレクトリ以下のパスリストを取得する
def find_all_files(directory):
    returnPathList = []
    for root, dirs, files in os.walk(directory):
#        yield root
        returnPathList.append(root)
        for file in files:
#            yield os.path.join(root, file)
            returnPathList.append(root + '\\' + file)
    return returnPathList
#――――――――――――――――――――――――――――――――――――――――――――――――――――――――

#――――――――――――――――――――――――――――――――――――――――――――――――――――――――
#OpenCV画像読み込み(日本語パス対応版)
def imread(filename, flags=cv2.IMREAD_COLOR, dtype=np.uint8):
    try:
        n = np.fromfile(filename, dtype)
        img = cv2.imdecode(n, flags)
        return img
    except Exception as e:
        print(e)
        return None
#――――――――――――――――――――――――――――――――――――――――――――――――――――――――

#――――――――――――――――――――――――――――――――――――――――――――――――――――――――
#OpenCV画像書き込み(日本語パス対応版)
def imwrite(filename, img, params=None):
    try:
        ext = os.path.splitext(filename)[1]
        result, n = cv2.imencode(ext, img, params)

        if result:
            with open(filename, mode='w+b') as f:
                n.tofile(f)
            return True
        else:
            return False
    except Exception as e:
        print(e)
        return False
#――――――――――――――――――――――――――――――――――――――――――――――――――――――――

#――――――――――――――――――――――――――――――――――――――――――――――――――――――――
#基となるデータをDataFrame形式で読みだす
def LoadBaseData(inFP, inUseCol):
    outDf = pd.read_csv(inFP, engine = "python", usecols = inUseCol)
    return outDf
#――――――――――――――――――――――――――――――――――――――――――――――――――――――――

#――――――――――――――――――――――――――――――――――――――――――――――――――――――――
#ディレクトリ構造のコピー
def CopyDirTree(inDir,  #入力dir
                outDir, #出力dir
                dirIsNeed,      #ディレクトリ構造をコピーするか？
                fileIsNeed,     #ファイルもコピーするか？
                CopyOrMove):    #コピーするか移動するか?
    for root, dirnames, filenames in os.walk(inDir):
        dirname = root.replace(inDir, "")   #入力dirの名前を除去
        #コピー条件による分岐
        if True == dirIsNeed:
            #ディレクトリ構造のコピー
            if not os.path.exists(outDir + dirname):
                os.makedirs(outDir + dirname)
                #サブディレクトリがあればそれもコピーする
                for dir in dirnames:
                    if not os.path.exists(outDir + dirname + '\\' + dir):
                        os.makedirs(outDir + dirname + '\\' + dir)
            #ファイル構造のコピー
            if True == fileIsNeed:
                for filename in filenames:
                    if 'Copy' == CopyOrMove:
                        shutil.copy(root + '\\' + filename, outDir + dirname + '\\' + filename)
                    elif 'Move' == CopyOrMove:
                        shutil.move(root + '\\' + filename, outDir + dirname)
            else:
                # do nothing
                pass
        else:
            #ディレクトリはコピーしない
            if True == fileIsNeed:
                for filename in filenames:
                    if 'Copy' == CopyOrMove:
                        shutil.copy(root + '\\' + filename, outDir + '\\' + filename)
                    elif 'Move' == CopyOrMove:
                        shutil.move(root + '\\' + filename, outDir)
            else:
                #do nothing
                pass
#――――――――――――――――――――――――――――――――――――――――――――――――――――――――
#ヒストグラムの作成
def createHist(plt, inList, bin):
    plt.hist(inList, bins= bin)
    return plt
#――――――――――――――――――――――――――――――――――――――――――――――――――――――――
#==============================================================
