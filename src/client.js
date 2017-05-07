var HTTPClient = require('httpclient');
var readline = require('readline');
var token = "";
var rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout,
  terminal: false
});

rl.on('line', function(line){
    console.log(line);
    if(line == "setup"){
		var options = {
		    hostname: 'http://ed744996.ngrok.io',
		    path: '/',
		    method: 'GET',
		    headers: {
		      'Authorization': "authorization " + new Buffer('8D0dZXMIBeiWSj7:YzDVJPRyIUp7DS0').toString('base64'),
		    }
		};
		// console.log(options);
		  var client = new HTTPClient(options)
		  client.request('/api/gettoken', function (err, res, body) {
		    console.log('error', err);
		    console.log('response', res);
		    console.log('body', JSON.parse(body.toString()).token);
		    token = JSON.parse(body.toString()).token;
		  });
    }else if(line == "removed"){
		 var options = {
		    hostname: 'http://ed744996.ngrok.io',
		    path: '/',
		    port: 80,
		    secure: false,
		    method: 'PUT',
		    body: {f_connected: false}
		  };

		  var client = new HTTPClient(options)
		  client.request('/api/hanger/:i&token='+token, function (err, res, body) {
		    console.log('error', err);
		    console.log('response', res);
		    console.log('body', JSON.parse(body.toString()));
		  });
    }else if(line == "deposit"){
 		var options = {
		    hostname: 'http://ed744996.ngrok.io',
		    path: '/',
		    port: 80,
		    secure: false,
		    method: 'PUT',
		    body: {f_connected: true}
		  };

		  var client = new HTTPClient(options)
		  client.request('/api/hanger/:i&token='+token, function (err, res, body) {
		    console.log('error', err);
		    console.log('response', res);
		    console.log('body', JSON.parse(body.toString()));
		  });
    }
});

 // var options = {
 //    hostname: 'http://2bb05442.ngrok.io',
 //    path: '/',
 //    port: 80,
 //    secure: false,
 //    method: 'GET',
 //    headers: {
 //      'x-powered-by': 'HTTPClient.js'
 //    },
 //    body: 'hello'
 //  }

 //  var client = new HTTPClient(options)
 //  client.request('/api/hanger/:i&token='+token, function (err, res, body) {
 //    console.log('Example 1')
 //    console.log('error', err)
 //    console.log('response', res)
 //    console.log('body', body)
 //  })