function ByteArrayToNum(bytes) {
  let value=0;
  for(let i=0;i<bytes.length;i++){
    value=(value<<8)+(bytes[i]&0xff);
  }
  return value;
}

function readBox(input_stream) {
  var size=[];
  for(var i=0;i<4;++i){
    var code=input_stream.charCodeAt(i);
    size=size.concat([code]);
  }
  let size_num=ByteArrayToNum(size);
  console.log(size_num);
  input_stream=input_stream.slice(4,);
  // console.log(input_stream);
  let type=input_stream.slice(0,4);
  console.log(type);
  input_stream=input_stream.slice(size_num-4,);
  
  return input_stream;
}
