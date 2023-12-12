let ft_list;
let cookies = [];

$(document).ready(function () {
    $('#new').on('click', newTodo);
    ft_list = $('#ft_list');
    let cookie = document.cookie;
    if (cookie) {
        cookies = JSON.parse(cookie);
        cookies.forEach(function (c) {
            addTodo(c);
        });
    }
});

$(window).on('unload', function () {
    let todo = ft_list.children();
    let cookies = [];
    for (let i = 0; i < todo.length; i++) {
        cookies.unshift(todo[i].innerHTML);
    }
    document.cookie = JSON.stringify(cookies);
});

function newTodo() {
    let todo = prompt('Veuillez entrer votre todo:', '');
    if (todo) {
        addTodo(todo);
    }
}

function addTodo(todo) {
    ft_list.prepend($('<div>' + todo + '</div>').on('click', deleteTodo));
}

function deleteTodo() {
    if (confirm('Voulez-vous vraiment retirer cette todo?')) {
        this.remove();
    }
}