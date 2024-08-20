// Note ChatGPT helped me develop this function.
function digUpSkeleton() {
    fetch('/resurrect', {
        method: 'POST',
    })
    .then(response => response.json())
    .then(data => {
        document.getElementById('skeleton-count').textContent = data.skeletonCount;
    });
}
