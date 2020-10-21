// import {ByteArrayToNum} from './util.js';
// 해당 디렉토리에서 npx http-server -c-1
function previewImage(f){
  var file=f.files;

  var reader = new FileReader();

  reader.onload=function(rst){
    document.getElementById('image_show').innerHTML='<img src="'+rst.target.result+'">';
    // console.log(rst.target.result);
  }

  reader.readAsDataURL(file[0]);
}

function previewVideo(f){
  var file=f.files;

  var reader = new FileReader();

  reader.onload=function(rst){
    document.getElementById('video_show').innerHTML='<video autoplay controls loop muted preload="none">'+'<source src="'+rst.target.result+'" type="video/mp4">'+'Error'+'</video>';
    // console.log(rst.target.result);
    let base64result=rst.target.result.split(',')[1];
    let decodedresult=atob(base64result);
    // console.log(typeof(decodedresult));
    // console.log(decodedresult);
    parseVideo(decodedresult);
  }

  reader.readAsDataURL(file[0]);
}

function parseVideo(decodedString){
  let input_stream=decodedString;
  readBox(input_stream);
}
