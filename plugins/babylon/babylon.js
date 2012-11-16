(function($){
  Drupal.behaviors.babylon = {
    attach: function(context) {
     $(document).bind("mouseup", function(){
       if($('.admintabs.translate.collapsible').length){
         reactOnMouseUp();
       }
     });
    }
  }
  function reactOnMouseUp(){
    var st = getSelected();
      if(st!=''){
        $('#translate-options').attr('text', st);
        translateText();
      }
  }
  function getSelected(){
      var t = '';
      if(window.getSelection){
        t = window.getSelection();
      }else if(document.getSelection){
        t = document.getSelection();
      }else if(document.selection){
        t = document.selection.createRange().text;
      }
      return t;
    }
  function translateText(){
    text = $('#translate-options').attr('text');
    $.ajax({
      url: Drupal.settings.basePath + Drupal.settings.adminTabs.modulePath + '/plugins/babylon/babylon.json.php',
      dataType: "json",
      type: "POST",
      data: {
        text: text,
        lang: 'nl'
      },
      success: function(data){
        $('.translate-trigger').html(Drupal.t('Select an option'));
        $('#translate-options').html(data);
      }
    });

  }
})(jQuery);


