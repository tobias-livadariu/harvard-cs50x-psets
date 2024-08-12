/* Setting the imageChosen variable to 0. */
let imageChosen = 0;

/* Defining the imageSwitcher function. */
function imageSwitcher()
{
    /* Defining a variable through which the dog image can be accessed. */
    let dogImage = document.getElementById('dog_image');

    /* Randomizing the imageChosen value to be between 1 and 5. */
    imageChosen = Math.floor(Math.random() * 5) + 1;

    /* Defining a variable to hold the new image address string. */
    let imageAddress = 
}
