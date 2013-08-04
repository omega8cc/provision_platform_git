<?php

/**
 * @file
 * Provides a pre-verify hook that will clone a site from Git
 * if the repo URL is specified.
 */

/**
 * Implements drush_hook_pre_provision_verify()
 */
function drush_provision_platform_git_pre_provision_verify() {
  if (d()->type === 'platform') {
    drush_log('CALLED');
    drush_log(print_r(d(), TRUE));
    if (!provision_file()->exists(d()->root)->status() && !empty(d()->provision_from_git)) {

      drush_log(dt("Platform path does not exist, cloning from Git"));
      drush_log(dt("Executing: " . 'git clone --recursive ' . excapeshellarg(trim(d()->repo_url)) . '--branch ' . escapeshellarg(trim(d()->repo_branch)) . ' ' . d()->root));

      // Clone the repo
      $output = exec('git clone --recursive -v' . excapeshellarg(trim(d()->repo_url)) . '--branch ' . escapeshellarg(trim(d()->repo_branch) . ' ' . d()->root), $output, $return_value);

      if ($return_value === 0) {
        drush_log(dt("Platform successfully cloned from Git"));
      }
      else {
        // We send back the full output if something went wrong.
        return drush_set_error("GIT_CLONE_FAILED", "Could not clone git repository. Output from Git: " . $output);
      }
    }
  }
}
