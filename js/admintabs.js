(function($){
  Drupal.behaviors.adminTabs = {
    attach: function(context) { 
      spinner_init();
    
      $('.tabs, #breadcrumb, .dev-query').not('.spinner').addClass('grow-tabs');
      tabexpander_init();

      $('.parent-tab').bind('click', function(event){
        event.preventDefault();
        var pid = $(this).attr('mlid');


        $('.child-tab[parent!=' + pid + ']').hide();
        $('.child-tab[parent=' + pid + ']').show();
      })

      $('.admintabs [process=backend] a').click(function(e){
        e.preventDefault();
        $('#adminspinner').toggle();
        $('#spinner-msg').html($(this).attr('href'));
        $.ajax({
          url: Drupal.settings.basePath + Drupal.settings.adminTabs.modulePath + '/includes/admintabs.callback.php',
          dataType: "json",
          type: "POST",
          data: {
            value: $(this).attr('href')
          },
          complete: function(data){
            setTimeout(function(){$('#adminspinner').toggle();}, 1000);
          }
        });
      });
    }
  }

  function tabexpander_init() {  
    $('.grow-tabs').bind('click', function(){
      $('ul.child-tab').hide();
      $(this).toggleClass('collapsible');
      $('.admintabs').not($(this)).not('.spinner').fadeToggle('fast');
    });
    $('.grow-tabs').children().bind('click', function(event){
      event.stopPropagation()
    });
  }
  
  function spinner_init() {
    var opts = {
      lines: 11, // The number of lines to draw
      length: 0, // The length of each line
      width: 6, // The line thickness
      radius: 15, // The radius of the inner circle
      corners: 1, // Corner roundness (0..1)
      rotate: 0, // The rotation offset
      color: '#FDFDFD',// #rgb or #rrggbb
      speed: 0.7, // Rounds per second
      trail: 60, // Afterglow percentage
      shadow: false, // Whether to render a shadow
      hwaccel: false, // Whether to use hardware acceleration
      className: 'spinner', // The CSS class to assign to the spinner
      zIndex: 2e9, // The z-index (defaults to 2000000000)
      top: 'auto', // Top position relative to parent in px
      left: 'auto' // Left position relative to parent in px
    };
    target = document.getElementById('adminspinner');
    var spinner = new Spinner(opts).spin(target);
  }
})(jQuery);