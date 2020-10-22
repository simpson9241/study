function readBoxInfo(input_stream,boxes,original_length){
  let size_byte=[];
  size_byte=ReadByte(4,input_stream);
  let size=ByteArrayToNum(size_byte);

  input_stream=input_stream.slice(4,);

  let type=input_stream.slice(0,4);
  input_stream=input_stream.slice(4,);

  input_stream=chooseBox(size,type,input_stream,boxes,original_length);

  input_stream=input_stream.slice(size-8,);

  return input_stream;
}

function chooseBox(size,type,input_stream,boxes,original_length){
  if(type=="ftyp"){
    let ftyp=setFTYP(size,type,input_stream,original_length,boxes);
    boxes.push(ftyp);
    printFTYP(ftyp);
    return input_stream;
  }else if(type=="free"){
    let free=setFREE(size,type,input_stream,original_length,boxes);
    boxes.push(free);
    // printFREE(free);
    return input_stream;
  }else{
    console.log("type: "+type);
    console.log("size: "+size);
    return input_stream;
  }
}

function readBox(input_stream,boxes) {
  let original_length=input_stream.length;
  while(input_stream.length>0){
    input_stream=readBoxInfo(input_stream,boxes,original_length);
  }
  console.log(boxes);
}
