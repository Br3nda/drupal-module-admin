// $Id: admin.menu.js,v 1.1.2.4 2010/01/10 18:54:24 yhahn Exp $

Drupal.behaviors.adminToolbarMenu = function(context) {
  if (jQuery().drilldown) {
    $('#admin-toolbar div.admin-block:has(ul.menu):not(.admin-toolbar-menu)')
      .addClass('admin-toolbar-menu')
      .each(function() {
        var menu = $(this);
        var trail = '#admin-toolbar div.admin-tab.' + $(this).attr('id').split('block-')[1] + ' span';
        menu.drilldown('init', {'activePath': Drupal.settings.activePath, 'trail': trail});

        // Replace the standard trail click handler with one that only
        // adjusts menu if the admin tab is active. Otherwise, switch
        // to that admin tab.
        menu.bind('refresh.drilldown', function() {
          $(trail + ' a').unbind('click').click(function() {
            if ($(this).parents('div.admin-tab').is('.admin-tab-active')) {
              if ($(this).siblings().size() !== 0) {
                var url = $(this).attr('href');
                var settings = {'activeLink': $('ul.menu a[href='+url+']', menu), 'trail': trail};
                menu.drilldown('setActive', settings);
                return false;
              }
              return true;
            }
            $(this).parents('div.admin-tab').click();
            return false;
          });
        });
      });
  }
};
