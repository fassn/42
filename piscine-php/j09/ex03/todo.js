let ft_list;

$(document).ready(function () {
    $('#new').on('click', newTodo);
    ft_list = $('#ft_list');
    getTodo();
});

function getTodo() {
    ft_list.empty();
    ajaxQuery('select.php', 'GET', null, function (data) {
        data = jQuery.parseJSON(data);
        console.log(data);
        jQuery.each(data, function (i, val) {
            ft_list.prepend($('<div data-id="' + i + '">' + val + '</div>').click(deleteTodo));
        })
    })
}

function newTodo() {
    let todo = prompt('Veuillez entrer votre todo:', '');
    if (todo) {
       ajaxQuery('insert.php?data=' + todo, 'GET', null, getTodo);
    }
}

function deleteTodo() {
    if (confirm('Voulez-vous vraiment retirer cette todo?')) {
        ajaxQuery('delete.php?id=' + $(this).data('id'), 'GET', null, getTodo);
    }
}

function ajaxQuery(url, method, data, success) {
    $.ajax({
        method: method,
        url: url,
        data: data
    })
        .done(function (data) {
            success(data);
        })
        .fail(function (msg) {
            console.log('error: ' + msg);
        });
}