let buttons = document.querySelectorAll('button');
let input = document.querySelector('#inputPart2');
let paragraph1 = document.querySelector('#part1Paragraph')
let paragraph2 = document.querySelector('#part2Paragraph')

/* Defining a function to process when the user clicks on a button. */
function buttonClick(id)
{
    id = '#' + id;
    if (id == '#rightAnswer')
    {
        let button = document.querySelector(id);
        paragraph1.textContent = "Correct!";
        paragraph1.style.color = 'green';
        button.style.color = 'green';
    }
    else if (id == 'submitPart2')
    {
        let textAnswer = input.value;
        if (textAnswer == "1.9")
        {
            paragraph2.textContent = "Correct!";
            paragraph2.style.color = 'green';
            input.style.color = 'green';
        }
        else
        {
            paragraph2.textContent = "Incorrect";
            paragraph2.style.color = 'red';
            input.style.color = 'red';
        }
    }
    else
    {
        let button = document.querySelector(id);
        paragraph1.textContent = "Incorrect";
        paragraph1.style.color = 'red';
        button.style.color = 'red';
    }
}


