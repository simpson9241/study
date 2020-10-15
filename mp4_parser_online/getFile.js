const fileSelector=document.getElementById('file-selector');
fileSelector.addEventListener('change',(event)=>{
  const file=event.target.files;
  console.log(file);
  readFile(file)
})

function readFile(file) {
  const reader=new FileReader();
  reader.addEventListener('load',(event)=>{
    // img.src=event.target.result;
    console.log(event.target.result)
  });
  // reader.readAsDataURL(file);
}
