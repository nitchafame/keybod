
// var noble = require('noble');

// //communication
// var MY_BEAN_UUID = "a495deadc5b14b44b5121370f02d74de";

// //Scan for bluetooth devices 
// noble.on('stateChange', function(state) {
//     if (state === 'poweredOn') {
//         noble.startScanning();
//         console.log('scanning...');
//     } else {
//         noble.stopScanning();
//         console.log('stopScanning');
//     }
// });

var Bean = require('ble-bean');
var twilio = require('twilio');
var client = new twilio.RestClient('AC0056d12eb7513b8693b5c18f0ff69027', '82ed1980d66e20991f09855506f16a19');

var intervalId;
var connectedBean;

console.log('app running, waiting for connection');

Bean.discover(function(bean){
  connectedBean = bean;
  process.on('SIGINT', exitHandler.bind(this));

  bean.on("serial", function(data, valid){
    console.log(data.toString());
    var consoleInput = data.toString();

    // clean up string of any linebreaks
    // https://stackoverflow.com/questions/10805125/how-to-remove-all-line-breaks-from-a-string
    consoleInput = consoleInput.replace(/(\r\n|\n|\r)/gm,"");

    if(consoleInput == '11'){
		sendTextMsg();     	
		console.log('sending message as reaction to input : ');
	    console.log(consoleInput);
    }
    else{
    	console.log('not sending any message, input is : ');
    	console.log(consoleInput);
    }

  });

  bean.on("disconnect", function(){
    process.exit();
  });

  bean.connectAndSetup(function(){

  });

});

process.stdin.resume();//so the program will not close instantly
var triedToExit = false;

//turns off led before disconnecting
var exitHandler = function exitHandler() {

  var self = this;
  if (connectedBean && !triedToExit) {
    triedToExit = true;
    console.log('Turning off led...');
    clearInterval(intervalId);
    connectedBean.setColor(new Buffer([0x0,0x0,0x0]), function(){});
    //no way to know if succesful but often behind other commands going out, so just wait 2 seconds
    console.log('Disconnecting from Device...');
    setTimeout(connectedBean.disconnect.bind(connectedBean, function(){}), 2000);
  } else {
    process.exit();
  }
};

//twilio
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
