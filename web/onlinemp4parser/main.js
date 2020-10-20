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
    console.log(decodedresult);
  }

  reader.readAsDataURL(file[0]);
}
