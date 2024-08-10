let buttons = document.querySelectorAll('button');
let form = document.querySelector('form');

/* Defining a function to process when the user clicks on a button. */
function buttonClick(id)
{
    id = '#' + id;
    if (id == '#rightAnswer')
    {
        let paragraph1 = document.querySelector('#part1Paragraph');
        let button = document.querySelector(id);
        paragraph1.textContent = "Correct!";
        paragraph1.style.color = 'green';
    }
    else
    {
        let paragraph1 = document.querySelector('#part1Paragraph');
        let button = document.querySelector(id);
        paragraph1.textContent = "Incorrect";
        paragraph1.style.color = 'red';
    }
}

function formSubmit()
