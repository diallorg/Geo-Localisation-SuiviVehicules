var express = require("express");
var app = express();
var bodyParser = require('body-parser')
var fs = require('fs');
const { CLIENT_RENEG_LIMIT } = require("tls");
const { v4 } = require('uuid')
// support parsing of application/json type post data
app.use(bodyParser.json());

//support parsing of application/x-www-form-urlencoded post data
app.use(bodyParser.urlencoded({ extended: true }));

//*****************************CHAUFFEUR****************

//LISTE CHAUFFEUR
app.get('/drivers', function (req, res) {
    const data  = fs.readFileSync('./drivers.json');
    var tmp = JSON.parse(data);
    console.log("drivers");
    res.send(tmp);
});

//AFFICHE UN CHAUFFEUR VIA SON ID
app.get('/drivers/:id', function (req, res) {
    const drivers = require('./drivers.json')
    const driver = drivers.find(
        (driver) => driver.id == req.params.id)
    res.send(driver);
});


//AJOUT CHAUFFEUR
app.post('/drivers/',  function (req, res) {
    var drivers = require("./drivers.json");
    console.log(req.body)
    const driver = {
        name: req.body.name,
        prenom: req.body.prenom,
        statut: req.body.statut,
        id: v4()    
    }
    drivers.push(driver);
    res.sendStatus(201);
    fs.writeFileSync('./drivers.json', JSON.stringify(drivers))
});

// AJOUT DE CLIENTS

app.post('/clients/',  function (req, res) {
    var clients = require("./clients.json");
    console.log(req.body)
    const client = {
        latitude: req.body.name,
        longitude: req.body.prenom,
        adresse: req.body.adresse,
        client: req.body.client,
        eta: req.body.eta,
        id: v4()    
    }
    clients.push(client);
    res.sendStatus(201);
    fs.writeFileSync('./clients.json', JSON.stringify(clients))
});

//LISTE DES CLIENTS

app.get('/clients', function (req, res) {
    const data  = fs.readFileSync('./clients.json');
    var tmp = JSON.parse(data);
    console.log("clients");
    res.send(tmp);
});

//LISTE VEHICULE
app.get('/vehicles', function (req, res) {
    const data  = fs.readFileSync('./vehicles.json');
    var tmp = JSON.parse(data);
    console.log("vehicles");
    res.send(tmp);
});

//AFFICHE UN VEHICULE VIA SON ID D'IMMATRICULATION

//AJOUT VEHICULE
app.post('/vehicles/',  function (req, res) {
    var vehicles = require("./vehicles.json");
    console.log(req.body)
    const vehicle = {
        plaque: req.body.plaque,
        VIN: req.body.VIN,
        id: v4()    
    }
    vehicles.push(vehicle);
    res.sendStatus(201);
    fs.writeFileSync('./vehicles.json', JSON.stringify(vehicles))
});



app.get('/', function (req, res) {
        res.sendFile(__dirname + '/index.html');
});




var server = app.listen(3001, () => {
    console.log("Server started");
});


