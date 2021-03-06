/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2011 Laszlo Papp <djszapi@archlinux.us>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef QGITDIFF_H
#define QGITDIFF_H

#include <QStringList>
#include <QMultiMap>
#include <git2/diff.h>

#include "qgitobject.h"
#include "qgittree.h"
#include "qgitrepository.h"
#include "qgittree.h"

namespace LibQGit2
{
    class QGitRepository;
    class QGitCommit;

    class LIBQGIT2_EXPORT QGitDiff : public QGitObject
    {
    public:
         QGitDiff(QGitRepository repo);

         virtual ~QGitDiff();

         QStringList getFileChangedList();

         QString getDeltasForFile(const QString &file);

         void diffCommits(QGitCommit commitFrom, QGitCommit commitTo);

         bool diffWorkingDir();

         /**
          * @brief print This function returns a QString representation of
          * 'git diff --patch'.
          * @return A QString.
          */
         QString print();

         // public so they can be called from the c callback code
         void addFileDiff(const char *delta);
         void addFileChanged(const git_diff_delta *delta);
         void addPatchHunks(const git_diff_delta *delta, const char *header, int headerLen);
         void addPatchLines(const git_diff_delta *delta, const char *line, char usage, int lineLen);
         void saveFullPatch(const char *line);

         /**
          * @brief diffStats This function generates a string that is equivlent to running
          * the command 'git diff --stats'. Makes the assumption that a diff has already occured
          * before calling this function. If it has not then an empty string is returned.
          * @return A string containing diff stats.
          */
         QString diffStats();

    private:
         struct patchInfo
         {
             QString patch;
             int additions;
             int deletions;
         };

         /**
          * @brief getDiffString helper function to print the +++--- for the diff stats
          * @param additions number of '+' to put into the string
          * @param deletions number of '-' to put into the string
          * @return a string which contains '+' for each addition and a '-' for each
          * deletion.
          */
         QString getDiffString(int additions, int deletions);

         QStringList fileList;
         // Maps filename to patch hunk
         QMap<QString, patchInfo> deltas;
         // Repo that contains the commits
         QGitRepository _repo;
         git_diff_list *diff;
         QString patch;

    };
}
#endif // QGITDIFF_H
