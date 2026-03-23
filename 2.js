<!DOCTYPE html> 
<head> 
<title>String Manipulation</title> 
<script> 
function isPalindrome1(str) { 
for (let i = 0; i < str.length / 2; i++) 
{ 
if (str.charAt(i) != str.charAt(str.length - 1 - i)) 
{
return false; 
} 
} 
return true; 
} 
function isPalindrome(str) 
{ 
let cleanedStr = str.replace(/[^A-Za-z0-9]/g, 
'').toLowerCase(); 
return cleanedStr === 
cleanedStr.split('').reverse().join(''); 
}
let userInput = prompt("Enter a string:"); 
let lengthOfString = userInput.length; 
Let extractedWord = userInput.includes("JavaScript") ? 
userInput.substring(userInput.indexOf("JavaScript"), 
userInput.indexOf("JavaScript") + "JavaScript".length) : "JavaScript not 
found"; 
let newString = userInput.replace("JavaScript", 
"TypeScript"); 
let palindromeCheck = isPalindrome(userInput);
console.log(`New String after Replacement: 
${newString}`); 
alert(`Length: ${lengthOfString}\nExtracted Word: ${extractedWord}\nNew 
String: ${newString}\nPalindrome: ${palindromeCheck}`); 
</script> 
</head> 
</html>

