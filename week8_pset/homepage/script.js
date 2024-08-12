/* Predefining the imageChosen variable. */
let imageChosen = -1;

/* Defining the imageSwitcher function. */
function imageSwitcher()
{
    /* Defining a variable through which the dog image can be accessed. */
    let dogImage = document.getElementById('dog_image');

    while (true)
    {
        /* Randomizing the imageChosen value to be between 1 and 5. */
        let newImageChosen = Math.floor(Math.random() * 4) + 1;

        if (newImageChosen != imageChosen)
        {
            imageChosen = newImageChosen;
            break;
        }
    }

    /* Defining a variable to hold the new image address string. */
    let imageAddress = "imgs/dog_image_" + imageChosen + ".png";
    dogImage.src = imageAddress;
}

// Putting the dog button in a variable
let dogButton = document.getElementById('dog_button');

// Randomizing the image when the document is loaded.
document.addEventListener('DOMContentLoaded', function() {
    imageSwitcher();
});

// Randomizing the image whenever the button is pressed.
dogButton.addEventListener('click', function() {
    imageSwitcher();
})
