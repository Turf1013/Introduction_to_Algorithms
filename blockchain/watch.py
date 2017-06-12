# coding: utf-8
import urllib2
import json
import smtplib
from email.mime.text import MIMEText
from email.mime.multipart import MIMEMultipart
import time
import Queue
import sys
from copy import deepcopy


queueLen = 6
myqueue = Queue.Queue(maxsize = queueLen)
gapTime=0
testIdx = 6

def AutoSendMail(content):
	msg = MIMEMultipart()
	msg['From'] = "qq332982511@163.com"
	msg['To'] = "496528674@qq.com"#改成自己邮箱
	msg['Subject'] = "Price Warring"
	msg["Accept-Language"]="zh-CN"
	msg["Accept-Charset"]="ISO-8859-1,utf-8"

	txt = MIMEText(content, 'plain', 'utf-8')
	msg.attach(txt)

	server = smtplib.SMTP()
	server.connect('smtp.163.com')
	server.login('qq332982511@163.com', 'les1026')
	server.sendmail(msg['From'], msg['To'], msg.as_string())
	server.quit()
	
def dealAnalysis(json,prejson,watchDict):
	global gapTime
	global testIdx
	
	# localtime=time.localtime(time.time())
	# print(json['display'])
	#print(localtime.tm_hour)
	#print(0.01*float(prejson['sum'])*24/float(localtime.tm_hour+1))
	#print(float(json['sum']))
	#print(float(prejson['sum']))
	#print(abs(float(json['sum']) - float(prejson['sum'])))
	coinName = str(json['coin_from'])
	
	if gapTime>0:
		gapTime=gapTime-1
		
	if coinName in watchDict:
		buyPrice,sellPrice = watchDict[coinName]
		curPrice = float(json['current'])
		if curPrice >= sellPrice:
			line = u"YUANBAO: " + 'name:' + str(json['coin_from']) + ', price:' + str(json['current'])
			AutoSendMail(line)
			print line
			gapTime=10	
			watchDict.pop(coinName)
			print watchDict
			
		# if curPrice>110 and testIdx>0:
			# line = u"YUANBAO: " + 'name:' + str(json['coin_from']) + ', price:' + str(json['current'])
			AutoSendMail(line)
			# print line
			# testIdx -= 1
		
		
def getJson(url):
	req = urllib2.Request(url)
	req.add_header("user-agent",
				   "Mozilla/5.0 (Windows NT 6.1; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/54.0.2840.99 Safari/537.36")
	page = urllib2.urlopen(req)
	html = page.read()
	html = html.decode("utf-8")
	# print(html)
	return	json.loads(html)

def watchPrice():
	watchDict = {
		'etc' : [117,125],
		'eth' : [1800,2500],
		'zec' : [1800,2500],
	}
	watchTmpDict = deepcopy(watchDict)
	print "watchPrice"
	initTimes = 0
	try:
		begTime = time.clock()
		while True:
			initTimes=initTimes+1
			s=getJson('https://www.yuanbao.com/coins/markets')
			coins=s['data']['cny']
			myqueue.put(coins)
			if initTimes >= queueLen:
				nowTime=time.strftime('%Y-%m-%d %H:%M:%S', time.localtime(time.time()))
				print(str(nowTime))
				precoins=myqueue.get()
				for i in range(len(coins)):
					coin=coins[i]
					precoin=precoins[i]
					dealAnalysis(coin,precoin,watchTmpDict)
				time.sleep(10)
				curTime = time.clock()
				if curTime-begTime >= 30*60:
					begTime = curTime
					watchTmpDict = deepcopy(watchDict)
	except:	
		print 'Linked error'
		
if __name__ == "__main__":
	reload(sys)
	sys.setdefaultencoding('utf-8')
	watchPrice()
