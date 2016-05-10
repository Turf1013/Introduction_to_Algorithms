var http = require('http');
var url = require('url');
http.createServer(function(req, res) {
	var urlobj = url.parse(req.url, true);
	var paths = [[parseInt(urlobj.query.id1), parseInt(urlobj.query.id2)]];
	res.end(JSON.stringify(paths));
}).listen(80)