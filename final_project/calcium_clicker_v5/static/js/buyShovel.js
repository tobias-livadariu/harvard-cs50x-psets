function buyShovel() {
    fetch('/buyShovel', {
        method: 'POST',
    })
    .then(response => response.json())
    .then(data => {
        shovelButton = document.getElementById('shovel-button')
        document.getElementById('total-skeletons').textContent = data.totalSkeletons;
    });
}
