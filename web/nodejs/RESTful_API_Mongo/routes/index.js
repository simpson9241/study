//routes/index.js

module.exports=function(app)
{
  //Get All Books
  app.get('/api/books',function(req,res){
    res.end();
  });

  //Get Single Book
  app.get('/api/books/:book_id',function(req,res){
    res.end();
  });

  //Get Book by Author
  app.get('/api/books/author/:author',function(req,res){
    res.end();
  });

  
}
