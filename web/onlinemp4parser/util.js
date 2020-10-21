function readBoxInfo(input_stream,boxes){
  var size_byte=[];
  for(var i=0;i<4;++i){
    var code=input_stream.charCodeAt(i);
    size_byte=size_byte.concat([code]);
  }
  let size=ByteArrayToNum(size_byte);
  // console.log(size_num);
  input_stream=input_stream.slice(4,);
  // console.log(input_stream);
  let type=input_stream.slice(0,4);
  // console.log(type);
  input_stream=input_stream.slice(4,);
  input_stream=chooseBox(size,type,input_stream,boxes);
  input_stream=input_stream.slice(size-8,);
  return input_stream;
}

function chooseBox(size,type,input_stream,boxes){
  if(type=="ftyp"){
    let ftyp=setFTYP(size,type,input_stream);
    boxes.push(ftyp);
    printFTYP(ftyp);
    return input_stream;
  }else{
    console.log("type: "+type);
    console.log("size: "+size);
    return input_stream;
  }
}

function readBox(input_stream) {
  let boxes=[];
  while(input_stream.length>0){
    input_stream=readBoxInfo(input_stream,boxes);
  }
  console.log(boxes);
}
