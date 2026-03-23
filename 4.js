<!DOCTYPE html> 
<head> 
<title>Event Listeners Experiment</title> 
</head> 
<body>
<button id="clickButton">Click Me</button> 
<!-- Experiment image with a reliable URL --> 
<img id="ExperimentImage" 
src="https://www.w3schools.com/html/img_chania.jpg" alt="Experiment Image" width="200"> 
<script> 
document.getElementById('clickButton').addEventListener('click' , function() 
{ 
console.log("Button clicked!"); 
});  document.getElementById('ExperimentImage').addEventListener('mouseover', function() { 
this.style.border = '5px solid red'; 
}); 
document.addEventListener('keydown', function(event) { 
console.log("Key pressed: " + event.key); 
}); 
document.getElementById('ExperimentImage').addEventListener('mouseout',function() {
this.style.border = 'none'; // remove the border 
}); 
</script> 
</body> 
</html>



