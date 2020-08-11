//app.js

//[Load Packages]
var express=require('express');
var app=express();
var bodyParser=require('body-parser');
var mongoose=require('mongoose');

//[Configure App to Use bodyParser]
app.use(bodyParser.urlencoded({extended:true}));
app.use(bodyParser.json());

//[Configure Server Port]
var port=process.env.PORT || 8080;

//[Configure Router]
var router=require('./routes')(app)

//[Run Server]
var server = app.listen(port, function(){
  console.log("Express server has started on port "+port);
})
