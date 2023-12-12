let ft_list;
let cookies = [];

window.onload = function () {
    document.getElementById('new').addEventListener('click', newTodo);
    ft_list = document.getElementById('ft_list');
    let cookie = document.cookie;
    if (cookie) {
        cookies = JSON.parse(cookie);
        cookies.forEach(function (c) {
            addTodo(c);
        });
    }
}

window.onunload = function () {
    let todo = ft_list.children;
    let cookies = [];
    for (let i = 0; i < todo.length; i++) {
        cookies.unshift(todo[i].innerHTML);
    }
    document.cookie = JSON.stringify(cookies);
}

function newTodo() {
    let todo = prompt('Veuillez entrer votre todo:', '');
    if (todo) {
        addTodo(todo);
    }
}

function addTodo(todo) {
    let new_todo = document.createElement('div');
    new_todo.innerHTML = todo;
    new_todo.addEventListener('click', deleteTodo);
    ft_list.insertBefore(new_todo, ft_list.firstChild);
}

function deleteTodo() {
    if (confirm('Voulez-vous vraiment retirer cette todo?')) {
        this.parentElement.removeChild(this);
    }
}