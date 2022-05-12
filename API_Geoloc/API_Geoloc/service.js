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
app.get('/chauffeur', function (req, res) {
    const data  = fs.readFileSync('./chauffeur.json');
    var tmp = JSON.parse(data);
    console.log("chauffeur");
    res.send(tmp);
});

//AFFICHE UN CHAUFFEUR VIA SON ID
app.get('/chauffeur/:id', function (req, res) {
    const chauffeurs = require('./chauffeur.json')
    const chauffeur = chauffeurs.find(
        (chauffeur) => chauffeur.id == req.params.id)
    res.send(chauffeur);
});


//AJOUT CHAUFFEUR
app.post('/chauffeur/',  function (req, res) {
    var chauffeurs = require("./chauffeur.json");
    console.log(req.body)
    const chauffeur = {
        name: req.body.name,
        prenom: req.body.prenom,
        statut: req.body.statut,
        id: v4()    
    }
    chauffeurs.push(chauffeur);
    res.sendStatus(201);
    fs.writeFileSync('./chauffeur.json', JSON.stringify(chauffeurs))
});


//LISTE VEHICULE
app.get('/vehicule', function (req, res) {
    const data  = fs.readFileSync('./vehicule.json');
    var tmp = JSON.parse(data);
    console.log("vehicule");
    res.send(tmp);
});

//AFFICHE UN VEHICULE VIA SON ID D'IMMATRICULATION

//AJOUT VEHICULE




app.get('/ ', function (req, res) {
        res.sendFile(__dirname + '/index.html');
});




var server = app.listen(8181);


