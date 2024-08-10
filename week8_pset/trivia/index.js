let buttons = document.querySelectorAll('button');
let input = document.querySelector('#inputPart2');
let paragraph = document.querySelector('#part1Paragraph')

/* Defining a function to process when the user clicks on a button. */
function buttonClick(id)
{
    id = '#' + id;
    if (id == '#rightAnswer')
    {
        let button = document.querySelector(id);
        paragraph.textContent = "Correct!";
        paragraph.style.color = 'green';
        button.style.color = 'green';
    }
    else if (id == 'submitPart2')
    {
        let 
    }
    else
    {
        let button = document.querySelector(id);
        paragraph.textContent = "Incorrect";
        paragraph.style.color = 'red';
        button.style.color = 'red';
    }
}


