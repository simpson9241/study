function setFTYP(size,type,input_stream,original_length,boxes) {
  let ftyp={
    struct_depth:0,
    size:size,
    type:"FileTypeBox",
    largesize:0,
    usertype:0,
    major_brand:'0',
    minor_version:0,
    compatible_brands:[],
    start_position:original_length-input_stream.length-8,
    end_position:original_length-input_stream.length+size-8
  }
  ftyp.major_brand=input_stream.slice(0,4);
  input_stream=input_stream.slice(4,);
  let minor_version_byte=[];
  minor_version_byte=ReadByte(4,input_stream);
  ftyp.minor_version=ByteArrayToNum(minor_version_byte);
  input_stream=input_stream.slice(4,);
  let compatible_brands_temp=input_stream.slice(0,size-16);
  for(let i=0;i<compatible_brands_temp.length/4;i++){
    ftyp.compatible_brands.push(compatible_brands_temp.slice(i*4,i*4+4));
  }
  // input_stream=input_stream.slice(size-16,);
  return ftyp;
}

function printFTYP(ftyp) {
  console.log("ftyp");
  console.log("Size: "+ftyp.size);
  console.log("Type: "+ftyp.type);
  console.log("Major Brand: "+ftyp.major_brand);
  console.log("Minor Version: "+ftyp.minor_version);
  console.log("Compatible Brands: "+ftyp.compatible_brands);

}
