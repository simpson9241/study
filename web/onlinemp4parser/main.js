// import {ByteArrayToNum} from './util.js';
// 해당 디렉토리에서 npx http-server -c-1
function previewImage(f){
  let file=f.files;

  let reader = new FileReader();

  reader.onload=function(rst){
    document.getElementById('image_show').innerHTML='<img src="'+rst.target.result+'">';
    // console.log(rst.target.result);
  }

  reader.readAsDataURL(file[0]);
}

function previewVideo(f){
  let file=f.files;
  let fileBlob=file[0];
  let url=(URL||webkitURL).createObjectURL(fileBlob);
  let video_parse_reader=new FileReader();
  document.getElementById('video_show').innerHTML='<video autoplay controls loop muted preload="none">'+'<source src="'+url+'" type="video/mp4">'+'Error'+'</video>';

  video_parse_reader.onload=function(rst){
    let data=rst.target.result;
    let array=new Uint8Array(data);
    console.log(data);
    console.log(array);
    // console.log(rst.target.result);;
    // console.log(typeof(rst.target.result));
    parseVideo(array);
  }
  console.log(fileBlob);
  // video_display_reader.readAsDataURL(file[0]);
  video_parse_reader.readAsArrayBuffer(fileBlob);
  // reader.readAsDataURL(file[0]);
}

function parseVideo(array){
  let input_stream=array;
  let boxes=[];
  readBox(input_stream,boxes);
}
