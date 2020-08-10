module.exports=function(app,fs)
{
  app.get('/',function(req,res){
    res.render('index',{
      title:"MY HOMEPAGE",
      length: 5
    })
  });

  app.get('/list',function(req,res){
    fs.readFile(__dirname+"/../data/"+"user.json",'utf8',function(err,data){
      console.log(data);
      res.end(data);
    });
  });

  app.get('/getUser/:username',function(req,res){
    fs.readFile(__dirname+"/../data/user.json",'utf8',function(err,data){
      var users=JSON.parse(data);
      res.json(users[req.params.username]);
    });
  });

  app.post('/addUser/:username',function(req,res){
    var result={};
    var username=req.params.username;

    //Check REQ Validity
    if(!req.body["password"] || !req.body["name"]){
      result["success"]=0;
      result["error"]="invalid request";
      res.json(result);
      return;
    }

    // Load Data & Check Duplication
    fs.readFile(__dirname+"/../data/user.json",'utf8',function(err,data){
      var users=JSON.parse(data);
      if(users[username]){
        //Duplication Found
        result["success"]=0;
        result["error"]="duplicate";
        res.json(result);
        return;
      }

      //Add to data
      users[username]=req.body;

      fs.writeFile(__dirname+"/../data/user.json",
                  JSON.stringify(users,null,'\t'),"utf8",function(err,data){
                    result={"success":1};
                    res.json(result);
                  })
    })
  });

  app.put('/updateUser/:username',function(req,res){
    var result={};
    var username=req.params.username;

    if(!req.body["password"] || !req.body["name"]){
      result["success"]=0;
      result["error"]="invalid request";
      res.json(result);
      return;
    }

    fs.readFile(__dirname+"/../data/user.json",'utf8',function(err,data){
      var users=JSON.parse(data);
      // Add/ Modify Data
      users[username]=req.body;

      //Save Data
      fs.writeFile(__dirname+"/../data/user.json",
                  JSON.stringify(users,null,'\t'),"utf8",function(err,data){
                    result={"success":1};
                    res.json(result);
                  })
    })
  });

  app.delete('/deleteUser/:username',function(req,res){
    var result={};
    fs.readFile(__dirname+"/../data/user.json","utf8",function(err,data){
      var users=JSON.parse(data);

      //If not Found
      if(!users[req.params.username]){
        result["success"]=0;
        result["error"]="not found";
        res.json(result);
        return;
      }

      //Delete from Data
      delete users[req.params.username];

      fs.writeFile(__dirname+"/../data/user.json",
                  JSON.stringify(users,null,'\t'),"utf8",function(err,data){
                    result["success"]=1;
                    res.json(result);
                    return;
                  })
    })
  })




}
