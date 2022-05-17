var fs=require('fs');
var data=fs.readFileSync('itineraire.json');
var itineraire=JSON.parse(data);
const express = require("express");
const app = express();
const port = 3000;
const cors=require('cors');
const { CLIENT_RENEG_LIMIT } = require('tls');
const bodyParser = require('body-parser')

app.use(bodyParser.json());
app.use(bodyParser.urlencoded({
	extended: true	
	})
);
app.use(express.static('public'));
app.use(cors());
app.get('/itineraire',alldata);
function alldata(request,response)
{
    response.send(itineraire);
}
app.get('/itineraire/:point/',searchElement);
function searchElement(request,response)
{
	var point=request.params.point;
	if(itineraire[point])
	{
		response.send(itineraire[point]); return;
	}
	response.status(400);
}

app.post('/itineraire', (req, res) => {
	res.send(req.body);
	fs.appendFile("./itineraire.json", ""+JSON.stringify(req.body),function(err){
		if(err) throw err;
		console.log('IS WRITTEN')
		});});

app.listen(port, () => console.log("Server Start at 3000 Port"));