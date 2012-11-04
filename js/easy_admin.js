(function($){
  
  
  Drupal.behaviors.featureBranches = {
    attach: function(context) { 
    $('.tabs, #breadcrumb, .dev-query').addClass('grow-tabs');
    tabexpander_init();
    
    $('.dev-query').click(function(){
      $('.devel-querylog').toggle();
    })
    
    $('.first.level').click(function(e){
      e.preventDefault();
      var trigger = $(this).attr('name');
      $('.subtabs[name='+trigger+']').addClass('fullblown');
      $('.subtabs[name!='+trigger+']').removeClass('fullblown');
    })
    }}

  function tabexpander_init() {  
  $('.grow-tabs').click(function(){
    $(this).toggleClass('collapsible');
    $('.easy_admin').not($(this)).fadeToggle('fast');
  });
  
  
  }
})(jQuery);


