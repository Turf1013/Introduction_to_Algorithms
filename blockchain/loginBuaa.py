#!/usr/bin/env python
import urllib
import urllib2
import json
import cookielib
import os
import time

def runRelogin():
    while True:
        try:
            flag=pingBaidu()
            if flag==None:
                time.sleep(30)
            else:
                testRequest()
        except:
            testRequest()
        time.sleep(60)

def pingBaidu():
    proc=os.popen('ping -n 1 baidu.com')
    return  proc.close()

def testRequest():
    data = {'action': 'login',
            'username': 'zy1506225',
            'password': '{B}YWJjZDEyMzQ=',
            'ac_id': 22,
            'ajax': 1}
    header = {
        "Accept": "*/*",
        "Accept-Encoding": "gzip, deflate",
        "Accept-Language": "zh-cn,zh;q=0.8,en-us;q=0.5,en;q=0.3",
        "Connection": "keep-alive",
        "Host": "gw.buaa.edu.cn:802",
        "Origin": "https: // gw.buaa.edu.cn: 802",
        "X - Requested - With": "XMLHttpRequest",
        "Referer": "https://gw.buaa.edu.cn:802/beihanglogin.php?ac_id=22&url=http://gw.buaa.edu.cn:802/beihangview.php",
        "User-Agent": "Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/49.0.2623.22 Safari/537.36 SE 2.X MetaSr 1.0"
    }
    reqData = urllib.urlencode(data)
    urllib2.build_opener()
    r=urllib2.Request('https://gw.buaa.edu.cn:802/include/auth_action.php',data=reqData,headers=header)
    # r.encoding='utf-8'
    # print(r.encoding)
    # print(r.text)
    print reqData
    print r
    reqTxt = urllib2.urlopen(r).read()
    print reqTxt


def getJsonWithCookie(url,data,rulfirst):
    header = {
        "Accept": "*/*",
        "Accept-Encoding": "gzip, deflate",
        "Accept-Language": "zh-cn,zh;q=0.8,en-us;q=0.5,en;q=0.3",
        "Connection": "keep-alive",
        "Host": "gw.buaa.edu.cn:802",
        "Origin": "https: // gw.buaa.edu.cn: 802",
        "X - Requested - With": "XMLHttpRequest",
        "Referer": "https://gw.buaa.edu.cn:802/beihanglogin.php?ac_id=22&url=http://gw.buaa.edu.cn:802/beihangview.php",
        "User-Agent": "Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/49.0.2623.22 Safari/537.36 SE 2.X MetaSr 1.0"
    }
    reqFirst=urllib2.Request(rulfirst)
    req = urllib2.Request(url, json.dumps(data).encode(), header)
    ##print(urllib.request.urlopen(req).read().decode('utf-8'))

    cj = cookielib.CookieJar()

    opener = urllib2.build_opener(urllib.request.HTTPCookieProcessor(cj))
    r = opener.open(reqFirst)
    print(cj)
    r = opener.open(req)
    print(r.status_code)
    print(r.read())

if __name__ =='__main__':
    data={'action':'login',
          'username':'zy1506225',
          'password':'{B}YWJjZDEyMzQ=',
          'ac_id': 22,
          'ajax':1}
    # getJsonWithCookie(r'https://gw.buaa.edu.cn:802/include/auth_action.php',data,r'https://gw.buaa.edu.cn:802/beihanglogin.php?ac_id=22&url=http://gw.buaa.edu.cn:802/beihangview.php')
    # testRequest()
    runRelogin()