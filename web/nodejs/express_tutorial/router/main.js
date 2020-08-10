module.exports=function(app,fs)
{
  app.get('/',function(req,res){
    var sess=req.session;

    res.render('index',{
      title:"MY HOMEPAGE",
      length: 5,
      name:sess.name,
      username:sess.username
    })
  });

  //세션 초기 설정
  app.get('/',function(req,res){
    sess=req.session;
  });

  //세션 변수 설정
  app.get('/login',function(req,res){
    sess=req.session;
    sess.username="velopert";
  });

  //세션 변수 사용
  app.get('/',function(req,res){
    sess=req.session;
    console.log(sess.username);
  });

  //세션 제거
  app.get('/',function(req,res){
    req.session.destroy(function(err){
    // cannot access session here
    })
  });


  //로그인 API
  app.get('/login/:username/:password',function(req,res){
    var sess;
    sess=req.session;

    fs.readFile(__dirname+"/../data/user.json","utf8",function(err,data){
      var users=JSON.parse(data);
      var username=req.params.username;
      var password=req.params.password;
      var result={};
      if(!users[username]){
        //Username Not Found
        result["success"]=0;
        result["error"]="not found";
        res.json(result);
        return;
      }

      if(users[username]["password"]==password){
        result["success"]=1;
        sess.username=username;
        sess.name=users[username]["name"];
        res.json(result);
      }else{
        result["success"]=0;
        result["error"]="incorrect";
        res.json(result);
      }
    })
  });

  //로그아웃 API
  app.get('/logout',function(req,res){
    sess=req.session;
    if(sess.username){
      req.session.destroy(function(err){
        if(err){
          console.log(err);
        }else{
          res.redirect('/');
        }
      })
    }else{
      res.redirect('/');
    }
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
  });




}
