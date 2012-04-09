(function($){
  
  
  Drupal.behaviors.featureBranches = {
    attach: function(context) { 
    $('.tabs, #breadcrumb, .dev-query').addClass('grow-tabs');
    tabexpander_init();
    
    $('.dev-query').click(function(){
      $('.devel-querylog').toggle();
    })
    }}

  function tabexpander_init() {  
  $('.grow-tabs').click(function(){
    $(this).toggleClass('collapsible');
    $('.easy_admin').not($(this)).fadeToggle('fast');
  });
  
  
  }
})(jQuery);


