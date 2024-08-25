/* Using a variable to limit the user's ability to
buy max autodiggers until the full transaction
has concluded. */
let canBuyMaxAutodiggers = true;

function buyMaxAutodiggers() {
    if (!canBuyMaxAutodiggers) {
        // Throw an error if canBuyMaxAutodiggers is false to prevent the function from running further
        throw new Error("Cannot buy ten autodiggers at the moment.");
    }
    canBuyMaxAutodiggers = false;

    fetch("numAutodiggersBuyable", {
        method: "POST",
    })
    .then(response => response.json())
    .then(async data => {
        /* Getting the max number of autodiggers the user can buy. */
        let numAutodiggersBuyable = data.numAutodiggersBuyable;
        if (numAutodiggersBuyable == 0) {
            throw new Error("Buy max transaction failed.");
        }

        /* Buying max autodiggers for the user. */
        for (let i = 0; i < numAutodiggersBuyable; i++) {
            await buyAutodigger();
        }
    })
    // Allow the next request to process after this one
    .finally(() => {
        canBuyMaxAutodiggers = true;
    })
    .catch(error => {
        console.error("Error during purchase:", error);
        canBuyMaxAutodiggers = true; // Reset the flag even if there is an error
    });
}
