
import React from 'react'; 
const issues = [ 
{ id: 1, title: 'Bug in Login', description: 'Error 404 on login', 
status: 'Open' }, 
{ id: 2, title: 'UI Issue on Dashboard', description: 'Misaligned 
elements', status: 'Closed' }, 
{ id: 3, title: 'API Timeout', description: 'Delayed response from 
server', status: 'Open' }, 
]; 
function IssueList() { 
return ( 
<div> 
<h1>Issue Tracker</h1> 
<ul> { } 
{issues.map(issue => ( 
<li key={issue.id}> { } 
<h2>{issue.title}</h2> { } 
<p>{issue.description}</p> { } 
<p>Status: {issue.status}</p> { }
</li> 
))}
 </ul> 
</div> 
); 
} 
export default IssueList; 
App.jsx
import React from 'react'; 
import IssueList from './IssueList'; 
function App() { 
return ( 
<div> 
<IssueList /> 
</div>
);
} export default App;


