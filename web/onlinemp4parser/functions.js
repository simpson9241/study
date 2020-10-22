function ByteArrayToNum(bytes) {
  let value=0;
  for(let i=0;i<bytes.length;i++){
    value=(value<<8)+(bytes[i]&0xff);
  }
  return value;
}
function ReadByte(num,input_stream){
  let byte_array=[];
  for(let i=0;i<num;i++){
    let code=input_stream.charCodeAt(i);
    byte_array=byte_array.concat([code]);
  }
  return byte_array;
}

function SetStructDepth(boxes,box){
  for(let i=boxes.length-1;i>=0;i--){
    if(boxes[i].end_position>box.start_position){
      box.struct_depth=boxes[i].struct_depth+1;
      return;
    }
  }
}
