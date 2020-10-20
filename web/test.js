function Rectangle(w,h) {
  var width=w;
  var height=h;

  this.getWidth=function(){
    return width;
  };

  this.getHeight=function(){
    return height;
  };

  this.setWidth=function(value){
    if(value<0){
      throw '길이는 음수일 수 없다';
    }else{
      width=value;
    }
  };

  this.setHeight=function(value){
    if(value<0){
      throw '길이는 음수일 수 없다';
    }else{
      height=value;
    }
  };
}
Rectangle.prototype.getArea = function () {
  return this.getWidth()*this.getHeight();
};

function Square(length) {
  this.base=Rectangle;
  this.base(length,length);
}

Square.prototype=Rectangle.prototype;

var r=new Rectangle(5,7);
var s=new Square(6);

console.log('Rectangle(5,7) : '+r.getArea()+'\nSqaure(6) : '+s.getArea());
