from urllib.request import urlopen
from bs4 import BeautifulSoup
import re
resultInfo=[]
resultTitle=[]
resultDate=[]
i=0
for o in range(80):
    html = urlopen("https://movies.yahoo.com.tw/movie_intheaters.html?page="+str(o))
    bsObj = BeautifulSoup(html)#根據css樣式表查詢
    nameList = bsObj.findAll("div", {"class":"release_btn color_btnbox"}) 
    for name in nameList: 
        intro = urlopen(str(name.a['href']))
        bsObj1 = BeautifulSoup(intro)#根據css樣式表查詢
        p = bsObj1.findAll("link", {"rel":"amphtml"}) 
        for b in p:
            #print(str(b['href']))
            index = urlopen(str(b['href']))
            bsObj2 = BeautifulSoup(index)#根據css樣式表查詢
            g = bsObj2.findAll("div", {"class":"plot-intro-txt limit"}) 
            f = bsObj2.findAll("div", {"class":"main-detail-info"})
            #h = bsObj2.find_all("div", {"class":"main-detail-info"})
            for c in g:
                resultInfo.append(str(re.sub('[a-zA-Z<p></p>="()\-6 ]','',str(c))))
            for d in f:
                resultTitle.append(str(re.sub('[a-zA-Z0-9<p></p>="()!設定該的為\- ]','',str(d.h2))))
            #for e in f:
             #   resultDate.append(str(re.sub('[a-zA-Z</p>="()!設定該的為\ ]','',str(e.span))))
IN = "asda"
while(IN !="Exit"):            
    IN=input('請輸入你想知道的電影:')
    for j in range(len(resultTitle)):
        if(IN in resultTitle[j]):
            print(resultTitle[j])
            print(resultInfo[j])