function buyShovel() {
    fetch('/buyShovel', {
        method: 'POST',
    })
    .then(response => response.json())
    .then(data => {
        let shovelButton = document.getElementById('shovel-button');
        let curShovel = data.curShovel;
        let maxShovel = data.maxShovel;
        let shovels = data.shovels;
        let shovelCost = data.shovelCost;

        if (curShovel < maxShovel) {
            shovelButton.textContent = "Forge a ${shovels[curShovel + 1]} shovel (cost: ${shovelCost} skeletons)";
        } else {
            shovelButton.textContent = "Your shovel is max level!";
        }
    });
}
