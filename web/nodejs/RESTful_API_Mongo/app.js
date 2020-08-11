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
//process.env.PORT 는 리눅스 터미널에서 export PORT [포트 번호] 로 변수 설정해줘야된다.
var port=process.env.PORT || 8080;



//[Run Server]
var server = app.listen(port, function(){
  console.log("Express server has started on port "+port);
})

//[Configure to MongoDB Server]
var db=mongoose.connection;
db.on('error',console.error);
db.once('open',function(){
  console.log("Connected to mongod server");
});

//Connect to MongoDB Server
mongoose.connect('mongodb://localhost/mongodb_tutorial')

//Define model
var Book=require('./models/book');

//[Configure Router]
var router=require('./routes')(app,Book);
