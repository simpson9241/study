function setFREE(size,type,input_stream,original_length,boxes){
  let free={
    struct_depth:0,
    size:size,
    type:"FreeBox",
    largesize:0,
    start_position:original_length-input_stream.length-8,
    end_position:original_length-input_stream.length-8+size,
  }
  SetStructDepth(boxes,free);
  return free;
}

function printFREE(free){
  console.log("free");
  console.log("Size: "+free.size);
  console.log("Type: "+free.type);
}
