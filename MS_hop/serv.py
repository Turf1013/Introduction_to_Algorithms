#! /usr/bin/env python
# -*- coding: utf-8 -*-

# from BaseHTTPServer import HTTPServer, BaseHTTPRequestHandler
# from urllib import urlparse as parse
import urlparse
import BaseHTTPServer

def solution(params):
    '''
    params: [('id1': '123'), ('id2': '456')]
    return: [[1,2,3], [3,4,5]]
    '''
    return "[[123,456]]"

class AppHandler(BaseHTTPServer.BaseHTTPRequestHandler):
    def do_GET(self):
        req = urlparse.parse_qsl(urlparse.urlparse(self.path).query)
        print req
        res = solution(req)
		self.send_response(200, 'OK')
        self.wfile.write(res)
        self.wfile.flush()
        # self.connection.close()
		
    def do_POST(self):
        self.do_GET()

def run(handler):
    addr = ('', 80)
    httpd = BaseHTTPServer.HTTPServer(addr, handler)
    try:
        httpd.serve_forever()
    except KeyboardInterrupt:
        httpd.server_close()

if __name__ == '__main__':
    run(AppHandler)


