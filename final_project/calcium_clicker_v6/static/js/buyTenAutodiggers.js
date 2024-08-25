/* Using a variable to limit the user's ability to
buy ten autodiggers until the full transaction
has concluded. */
let canBuyTenAutodiggers = true;

function buyTenAutodiggers() {
    if (!canBuyTenAutodiggers) {
        // Throw an error if canBuyTenAutodiggers is false to prevent the function from running further
        throw new Error("Cannot buy ten autodiggers at the moment.");
    }
    canBuyTenAutodiggers = false;

    fetch("numAutodiggersBuyable", {
        method: "POST",
    })
    .then(response => response.json())
    .then(async data => {
        /* Getting the max number of autodiggers the user can buy. */
        let numAutodiggersBuyable = data.numAutodiggersBuyable;
        if (numAutodiggersBuyable < 10) {
            throw new Error("10x transaction failed.");
        }

        /* Buying 10 autodiggers for the user. */
        for (let i = 0; i < 10; i++) {
            await buyAutodigger();
        }
    })
    // Allow the next request to process after this one
    .finally(() => {
        canBuyTenAutodiggers = true;
    })
    .catch(error => {
        console.error("Error during purchase:", error);
        canBuyTenAutodiggers = true; // Reset the flag even if there is an error
    });
}
