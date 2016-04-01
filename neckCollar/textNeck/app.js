
var noble = require('noble');

//communication
var MY_BEAN_UUID = "a495deadc5b14b44b5121370f02d74de";

//Scan for bluetooth devices 
noble.on('stateChange', function(state) {
    if (state === 'poweredOn') {
        noble.startScanning();
        console.log('scanning...');
    } else {
        noble.stopScanning();
        console.log('stopScanning');
    }
});


var twilio = require('twilio');
console.log("The text message sent!");

var client = new twilio.RestClient('AC0056d12eb7513b8693b5c18f0ff69027', '82ed1980d66e20991f09855506f16a19');

sendTextMsg(); 

function sendTextMsg(){
	client.sms.messages.create({
	    to:'+13477712705',
	    from:'+16313971313',
	    body:'You have been look at this screen for so long!'
	}, function(error, message) {
	    // The HTTP request to Twilio will run asynchronously. This callback
	    // function will be called when a response is received from Twilio
	    // The "error" variable will contain error information, if any.
	    // If the request was successful, this value will be "falsy"
	    if (!error) {
	        // The second argument to the callback will contain the information
	        // sent back by Twilio for the request. In this case, it is the
	        // information about the text messsage you just sent:
	        console.log('Success! The SID for this SMS message is:');
	        console.log(message.sid);
	 
	        console.log('Message sent on:');
	        console.log(message.dateCreated); 
	    } else {
	        console.log('Oops! There was an error.');
	    }
	});
}
