
// bleh.. this doesn't work with my lazy admin tabs.. '


(function($){
  Drupal.behaviors.babylon = {
    attach: function(context) {
     $(document).bind("mouseup", reactOnMouseUp);
     $('#translate_link').bind("click", translateText);
    }
  }
  function reactOnMouseUp(){
    var st = getSelected();
      if(st!=''){
        $('#translate_options').attr('text', st);
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
    text = $('#translate_options').attr('text');
    console.log(text, 'translate me!');
    $.ajax({
      url: Drupal.settings.basePath + Drupal.settings.lazy_admin.modulePath + '/plugins/babylon/babylon.json.php',
      dataType: "json",
      type: "POST",
      data: {
        text: text,
        lang: 'nl'
      },
      success: function(data){
        $('#translate_options').append(data);
      }
    });

  }
})(jQuery);


