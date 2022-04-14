var fs=require('fs');
var data=fs.readFileSync('drivers.json');
var drivers=JSON.parse(data);
const express = require("express");
const app = express();
const port = 3000;
const cors=require('cors');
const nodeCron = require("node-cron");
const qrcode = require('qrcode-terminal');

const SESSION_FILE_PATH = './session.json';

app.listen(port, () => console.log("Server Start at 3000 Port"));

app.use(express.static('public'));
app.use(cors());
app.get('/drivers',alldata);
function alldata(request,response)
{
    response.send(elements);
}
app.get('/drivers/:driver/',searchElement);
function searchElement(request,response)
{
	var word=request.params.driver;
	word=word.charAt(0).toUpperCase()+word.slice(1).toLowerCase();
	console.log(word);
	if(drivers[word])
	{
		var reply=drivers[word];
		
	}
	else
	{
		var reply={
			status:"Not Found"
		}
	}
    console.log(reply.boil);
	response.send(reply);

}

const { Client, LegacySessionAuth } = require('whatsapp-web.js');

let sessionData;
if(fs.existsSync(SESSION_FILE_PATH)) {
    sessionData = require(SESSION_FILE_PATH);
}

// Use the saved values
const client = new Client({
    authStrategy: new LegacySessionAuth({
        session: sessionData
    })
});

client.on('qr', qr => {
    qrcode.generate(qr, {small: true});
});

client.on('ready', () => {
    console.log('Client is ready!');
    
});

const job = nodeCron.schedule("0 0 9 * * *", function jobYouNeedToExecute() {
    client.getChats().then(chats => {
		const MyGroup = chats.find((chat) => chat.name === "Geoloc");
	//console.log(MyGroup);
	client.sendMessage(MyGroup.id._serialized, "")
});
  });

  const job1 = nodeCron.schedule("0 30 9 * * *", function jobYouNeedToExecute() {
    client.getChats().then(chats => {
		const MyGroup = chats.find((chat) => chat.name === 'Geoloc');
	//console.log(MyGroup);
	client.sendMessage(MyGroup.id._serialized, "")
});
  });

  const job4 = nodeCron.schedule("0 30 10 * * *", function jobYouNeedToExecute() {
    client.getChats().then(chats => {
		const MyGroup = chats.find((chat) => chat.name === 'Geoloc');
	//console.log(MyGroup);
	client.sendMessage(MyGroup.id._serialized, "")
});
  });

  const job3 = nodeCron.schedule("0 0 16 * * *", function jobYouNeedToExecute() {
    client.getChats().then(chats => {
		const MyGroup = chats.find((chat) => chat.name === 'Geoloc');
	//console.log(MyGroup);
	client.sendMessage(MyGroup.id._serialized, "")
});
  });

  const job2 = nodeCron.schedule("0 0 17 * * *", function jobYouNeedToExecute() {
    client.getChats().then(chats => {
		const MyGroup = chats.find((chat) => chat.name === 'Geoloc');
	//console.log(MyGroup);
	client.sendMessage(MyGroup.id._serialized, "")
});
  });

  client.on('authenticated', (session) => {
    sessionData = session;
    fs.writeFile(SESSION_FILE_PATH, JSON.stringify(session), (err) => {
        if (err) {
            console.error(err);
        }
    });
});

client.on('message', message => {
	if(message.body === '!drivers') {
	client.sendMessage(MyGroup.id._serialized, "LIVREURS :")
	}
});

client.initialize();