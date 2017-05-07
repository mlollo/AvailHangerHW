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
    if(line.split(" ")[0] == "setup"){
		var options = {
		    hostname: 'localhost',
		    path: '/',
		    port: 9004,
		    method: 'GET',
		    headers: {
		      'Authorization': "authorization " + new Buffer('8D0dZXMIBeiWSj7:YzDVJPRyIUp7DS0').toString('base64'),
		    }
		};
		// console.log(options);
		  var client = new HTTPClient(options);
		  client.request('/api/gettoken', function (err, res, body) {
		    console.log('error', err);
		    console.log('response', res);
		    console.log('body', JSON.parse(body.toString()).token);
		    token = JSON.parse(body.toString()).token;
		  });
    }else if(line.split(" ")[0].split(":")[0] == "removed"){
    	 var  i = line.split(":")[1];

		 var options = {
		    hostname: 'localhost',
		    path: '/',
		    port: 9004,
		    secure: false,
		    method: 'PUT',
		    body: {f_connected: false}
		  };

		  var client = new HTTPClient(options)
		  client.request('/api/hanger/:'+i+'&token='+token, function (err, res, body) {
		    console.log('error', err);
		    console.log('response', res);
		    console.log('body', body);
		  });
    }else if(line.split(" ")[0].split(":")[0] == "deposit"){
    	var  i = line.split(":")[1];
 		var options = {
		    hostname: 'localhost',
		    path: '/',
		    port: 9004,
		    secure: false,
		    method: 'PUT',
		    body: {f_connected: true}
		  };

	  var client = new HTTPClient(options)
	  client.request('/api/hanger/:'+i+'&token='+token, function (err, res, body) {
	    console.log('error', err);
	    console.log('response', res);
	    console.log('body', body);
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