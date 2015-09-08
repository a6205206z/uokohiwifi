$(function(){
    var selectedHtml = "";
    var nowSelect = $(".my-select");
    nowSelect.after(selectedHtml);
    var selectNode = nowSelect.find('li');

    selectNode.on('dblclick', function(event) {
        event.preventDefault();
        var that = $(this);
            that.clone().appendTo(".my-selected>ul");
            $('.my-selected>ul').sortable().disableSelection();
            $(".my-selected .ui-sortable>li").on('dblclick', function(event) {
                event.preventDefault();
                $(this).remove();
            });
    });
        $(".form_datetime").datetimepicker({
         format: 'yyyy-mm-dd - hh:ii',
         autoclose:true,
         language: "zh-CN"
    });
})