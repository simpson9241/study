export function ByteArrayToNum(bytes) {
  let value=0;
  for(let i=0;i<bytes.length;i++){
    value=(value<<8)+(bytes[i]&0xff);
  }
  return value;
}
